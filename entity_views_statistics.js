(function ($) {
  $(document).ready(function () {
    $.get(Drupal.settings.basePath + 'entity_views_statistics/' + Drupal.settings.entity_views_statistics.entity_type + '/' + Drupal.settings.entity_views_statistics.entity_id);
  });
})(jQuery);